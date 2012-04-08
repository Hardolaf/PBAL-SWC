<?php
/**
 * @author Joseph 'Hardolaf' Warner <hardolaf@gmail.com>
 */
class DB {

    public $connected = false;
    public $host;
    public $user;
    public $pass;
    public $database = null;
    private $link;

    public function __construct($host = SERVICE_CONFIG_DB_SERVER, $user = SERVICE_CONFIG_DB_USER, $pass = SERVICE_CONFIG_DB_PASSWORD, $db = SERVICE_CONFIG_DB_DATABASE){
        if(!$host || !$user || !$pass){
            throw new Exception('No database settings supplied');
        }

        $this->host = $host;
        $this->user = $user;
        $this->pass = $pass;
        $this->link = $this->connect();
        if(!$this->link) {
            throw new Exception('Unable to connect to the database: '.mysql_error());
        }
        $this->changeDatabase($db);
    }

    /*public function __destruct() {
        if($this->link) {
            $this->close();
        }
    }*/

    public function connect(){
        $link = mysql_connect($this->host, $this->user, $this->pass);
        if(!$link){
            throw new SQLException('Could not connect to database');
        }
        unset($this->pass);

        //now connected
        $this->connected = true;
        return $link;
    }

    public function close() {
        return mysql_close($this->link);
    }

    public function changeDatabase($name = SERVICE_CONFIG_DB_DATABASE){
        $this->select($name);
        $this->database = $name;
    }

    public function query($query, $dbName = SERVICE_CONFIG_DB_DATABASE) {
        if(!$this->connected){
            $this->connect();
            $this->changeDatabase($dbName);
        }

        $primaryDB = $this->database;
        if($dbName != $this->database) {
            $this->changeDatabase($dbName);
        }

        //can't confuse it with db_prepare
        if(func_num_args() > 2) {
            throw new InvalidArgumentException('DB query takes 1 (maximum of 2) args');
        }

        $res = mysql_query($query);

        //on failure, die
        if(!$res) {
            throw new Exception($this->error() . ' => ' . htmlentities($query));
        }

        //switching back to default if was set earlier
        if($dbName != $primaryDB) {
            $this->changeDatabase($primaryDB);
        }

        return $res;
    }

    public function getTableFields($strTableName) {
        $resTable = db_query('SELECT * FROM '.$this->escape($strTableName).' LIMIT 1');
        $intFieldCount = mysql_num_fields($resTable);

        $arrResult =  array();
        for ($x = 0; $x < $intFieldCount; $x++) {
            $arrResult[] = mysql_field_name($resTable, $x);
        }
        return $arrResult;
    }

    public function select($tableName) {
        $db_selected = mysql_select_db($tableName);

        if (!$db_selected) {
            throw new Exception($this->error());
        }
        return true;
    }

    public function error() {
        return mysql_error() ;
    }

    public function affected_rows($link_identifier=null) {
        if (!is_null($link_identifier)) {
            return mysql_affected_rows($link_identifier);
        }
        return mysql_affected_rows();
    }

    public function fetch_object($result) {
        return mysql_fetch_object($result);
    }

    public function fetch_array($result) {
        return mysql_fetch_array($result);
    }

    public function fetch_assoc($result) {
        return mysql_fetch_assoc($result);
    }

    public function num_rows($result) {
        return mysql_num_rows($result);
    }

    public function num_fields($result) {
        return mysql_num_fields($result);
    }

    public function field_type($result, $intOffset) {
        return mysql_field_type($result, $intOffset);
    }

    public function field_len($result, $intOffset) {
        return mysql_field_len($result, $intOffset);
    }

    public function field_name($result, $intIndex) {
        return mysql_field_name($result, $intIndex);
    }

    public function foreign_key_checks($mode = true){
        if($mode){
            $this->query('SET foreign_key_checks = 1;');
        } else {
            $this->query('SET foreign_key_checks = 0;');
        }
    }

    public function insert_id($link_identifier=null) {
        if (!is_null($link_identifier)) {
            return mysql_insert_id($link_identifier);
        }
        return mysql_insert_id();
    }

    public function free_result($result) {
        return mysql_free_result($result);
    }

    public function result($result, $row,  $field=null) {
        return  mysql_result($result, $row,  $field);
    }

    public function escape($strToBeEscaped, $intLinkIndentifier=null) {
        if (!is_null($intLinkIndentifier) && !is_numeric($strToBeEscaped)) {
            return mysql_real_escape_string($strToBeEscaped, $intLinkIndentifier);
        } elseif (!is_numeric($strToBeEscaped)) {
            return mysql_real_escape_string($strToBeEscaped);
        }
        return $strToBeEscaped;
    }

    public function quote_escape($value){
        if($value === null){
            return 'null';
        } else if($value === true){
            return 1;
        } else if($value === false){
            return 0;
        }
        if(is_array($value)){
            $value = array_map('$this->quote_escape', $value);
            return '(' . implode(', ', $value) . ')';
        }
        if(is_numeric($value)){
            return $value;
        }
        return '"' . $this->escape($value) . '"';
    }

    public function filter(array $conditions = array(), $boolean = 'AND'){
        if(!$conditions){
            return null;
        }

        $implode = array();
        foreach($conditions as $key => $value){
            if(is_array($value)){
                $implode[] = '`'.$key.'` IN '.$this->quote_escape($value);
            } else {
                $implode[] = '`'.$key.'` = '.$this->quote_escape($value);
            }
        }
        return implode(' '.$boolean.' ', $implode);
    }

    public function fetch_row($resResult) {
        return mysql_fetch_row($resResult);
    }

    public function get_rows($resResult, $class=null, $assoc=null) {
        $arr = array();
        while($row = $this->fetch_object($resResult, $class)){
            if($assoc){
                $arr[$row->$assoc] = $row;
            } else {
                $arr[] = $row;
            }
        }
        return $arr;
    }

    public function get_array($resResult){
        $arr = array();
        $count = $this->num_rows($resResult);
        for($i = 0; $i < $count; $i++){
            $arr[] = $this->result($resResult, $i, 0);
        }
        return $arr;
    }

    public function single_result($resResult, $default = null){
        $count = $this->num_rows($resResult);
        if($count > 1){
            throw new InvalidArgumentException('db_single_result called on resource with more than one result row');
        }
        if($count == 0){
            return $default;
        }
        return $this->result($resResult, 0, 0);
    }

    public function db_schema($table, $foreignKeys = false, $autoIncrement = false) {
        if(!$res = $this->query("SHOW CREATE TABLE `$table`")){
            return $this->error();
        }
        $schema = $this->result($res, 0, 1);
        if($schema){
            //remove any lines that are setting foreign keys
            if(!$foreignKeys){
                $schema = preg_replace('/(,\\s*|\\s*|)^\\s*CONSTRAINT.*$/m', '', $schema);
            }
            if(!$autoIncrement){
                $schema = preg_replace('/AUTO_INCREMENT=\d+\s*/', '', $schema);
            }

            return $schema . ";\n\n";
        }
        return '';
    }

    public function prepare_assoc($query, array $assoc = array()){
        $numeric = 0;

        $callback = function($match) use($assoc, &$numeric){
            $modifier = $match[1];
            $name = $match[2];
            $db = new DB();

            if($modifier == '#'){
                if($name == 'UNIX_NOW'){
                    return time();
                }
                return $db->quote_escape(constant($name));
            }

            if($modifier == '@'){
                if(is_array($assoc[0])){
                    return $db->quote_escape($assoc[0][$name]);
                } else if(is_object($assoc[0])){
                    return $db->quote_escape($assoc[0]->$name);
                }
                throw new InvalidArgumentException('Invalid argument provided as assoc');
            }

            if($modifier == '!!'){
                if(!array_key_exists($numeric, $assoc)){
                    throw new InvalidArgumentException('Looking for array argument: ' . $numeric . ' but not found');
                }
                return $assoc[$numeric++];
            }

            if($modifier == '?'){
                if(!array_key_exists($numeric, $assoc)){
                    throw new InvalidArgumentException('Looking for array argument: ' . $numeric . ' but not found.');
                }
                return $db->quote_escape($assoc[$numeric++]);
            }

            if($modifier == '&&') {
                    return $assoc[$numeric++];
            }

            throw new InvalidArgumentException('Invalid query modified provided.');
        };

        return preg_replace_callback('/([@#?]|!!|&&)(\w*)/', $callback, $query);
    }

    public function prepare_array($query, $array){
        $query = $this->prepare_assoc($query, $array);
        return $this->query($query);
    }

    public function prepare(){
        $intArgs = func_num_args() - 1;
        $arrArgs = func_get_args();

        //some initial checking
        if($intArgs == -1){
            throw new Exception('db_prepare called with no arguments');
        }

        //wildcard query string
        $query = array_shift($arrArgs);

        //fill in the query
        $query = $this->prepare_assoc($query, $arrArgs);

        //run the generated query
        return $this->query($query);
    }

    public function pagination($sql, $perPage = 20, $page = 1){
        //add in the limit clause
        $sql .=' LIMIT ?, ?';

        //remove the regular args from the array
        $prepareArgs = func_get_args();
        array_shift($prepareArgs);
        array_shift($prepareArgs);
        array_shift($prepareArgs);

        //add pagination offset and limit
        $prepareArgs[] = ($page - 1) * $perPage;
        $prepareArgs[] = (int)$perPage;

        //pass off to prepare
        return $this->prepare_array($sql, $prepareArgs);
    }

    public function pagination_count($sql, $perPage = 10){
        //remove regular args from the array
        $prepareArgs = func_get_args();
        array_shift($prepareArgs);
        array_shift($prepareArgs);
        array_shift($prepareArgs);

        //pass off to prepare, and work out number of pages
        $total = count($this->prepare_array($sql, $prepareArgs));
        return $total / $perPage;
    }

    public function insert($table, $array){
        if(empty($array)){
            throw new InvalidArgumentException('Array is empty');
        }

        $sets = array();
        foreach($array as $key=>$value){
            if($value instanceof Entity){
                $sets[] = '`' . $key . 'Type` = ' . $this->quote_escape($value->entityType);
                $sets[] = '`' . $key . 'ID` = ' . $this->quote_escape($value->entityID);
            } else {
                $sets[] = '`' . $key . '` = ' . $this->quote_escape($value);
            }
        }

        $sql = 'INSERT INTO `' . $table . '` SET ' . implode(', ', $sets);
        $this->query($sql);

        return $this->insert_id();
    }

    public function insert_bulk($table, $array, $action = 'INSERT'){
        if(!in_array($action, array('INSERT', 'REPLACE'))){
            throw new InvalidArgumentException('Can only use INSERT or REPLACE');
        }

        if(empty($array)){
            throw new InvalidArgumentException('Array is empty');
        }

        $first = reset($array);

        $fieldkeys = array();
        $fields = array();
        foreach($first as $key=>$value){
            if($value instanceof Entity){
                $fields[] = '`' . $key . 'ID`, `' . $key.'Type`';
                $fieldkeys[] = $key;
            } else {
                $fields[] = '`' . $key . '`';
                $fieldkeys[] = $key;
            }
        }

        $sql = $action.' INTO `'.$table.'` (' . implode(', ', $fields).') VALUES ';
        $rows = array();
        foreach($array as $entry){
            $row = array();
            foreach($fieldkeys as $field){
                if(is_array($entry)){
                    $deref = $entry[$field];
                } else {
                    $deref = $entry->$field;
                }
                $row[] = $this->quote_escape($deref);
            }
            $rows[] = '(' . implode(', ', $row) . ')';
        }
        $sql = $sql . implode(', ', $rows);
        $result = $this->query($sql);

        $id = $this->insert_id();

        $ids = array();
        for($i = 0; $i < count($array); $i++) {
            $ids[] = $id + $i;
        }

        return $ids;
    }

    /**
    * Inserts or updates an associative array into $table. Field names are DB field names and values are values.
    * @param $table table name
    * @param array $array associative array/object of fields
    * @return insert ID if possible
    */
    public function insert_or_update($table, $array){
        if(empty($array)){
            throw new InvalidArgumentException('Array is empty');
        }

        $sets = array();
        foreach($array as $key=>$value){
            $sets[] = '`' . $key . '` = ' . $this->quote_escape($value);
        }

        $set = implode(', ', $sets);
        $sql = 'INSERT INTO `' . $table . '` SET ' . $set . ' ON DUPLICATE KEY UPDATE ' . $set;
        $this->query($sql);
        return $this->insert_id();
    }

    /**
    * Deletes from $table where row matching $array.
    *
    * @param string $table table name
    * @param array $array associative array/object of fields (ANDed together)
    * @return int number of affected rows
    */
    public function delete($table, $array, $limit = 0){
        //force it to be an array
        if(is_object($array)){
            $array = (array)$array;
        }

        //apply limits
        if($limit > 0){
            $limit = ' LIMIT ' . (int)$limit;
        } else {
            $limit = '';
        }

        //if filters are empty, means truncating the entire table
        if(empty($array)){
            $this->query('DELETE FROM `' . $table . '` ' . $limit);
            return $this->affected_rows();
        }

        //otherwise generate where from filter
        $filter = $this->filter($array);
        $this->query('DELETE FROM `'.$table.'` WHERE '.$filter.$limit);
        return $this->affected_rows();
    }

    public function truncate($table){
        return $this->query('DELETE FROM `'.$table.'`');        
    }
    
}

?>