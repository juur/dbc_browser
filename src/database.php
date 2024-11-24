<?php
require('config.php');
$db_conn = mysqli_connect($config['db_host'], $config['db_user'], $config['db_pass'], $config['dbc']);

function query_dbc($table, $id)
{
    global $config, $db_conn;
    $query = "SELECT * FROM $table WHERE id = $id;";
    $result = mysqli_query($db_conn, $query) or die(mysqli_error());
    $num_rows = mysqli_num_rows($result);
    if ($num_rows > 1) die("Error: got $num_rows rows searching for primary key value $id in table $table, expected 1");
    return array($result, $num_rows);
}

function query_world($table, $id)
{
    global $config, $db_conn;
    $query = "SELECT * FROM $table WHERE entry = $id";
    $result = mysqli_query($db_conn, $query) or die(mysqli_error());
    $num_rows = mysqli_num_rows($result);
    if ($num_rows > 1) die("Error: got $num_rows rows searching for primary key value $id in table $table, expected 1");
    return array($result, $num_rows);
}
?>
