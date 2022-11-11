<?php
    header("Access-Control-Allow-Origin: *");
    header("Content-Type: application/json; charset=UTF-8");
    header("Access-Control-Allow-Methods: GET");
    header("Access-Control-Max-Age: 3600");
    header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");
    header('Content-Type: application/json');

    $data = json_decode(file_get_contents("php://input"));
    include('../config/dbcon.php');
    
    if(isset($_GET['id'])) {
        $id = $_GET['id'];
        $read = "SELECT * FROM `register` WHERE `id` = $id";
        $result = $conn->query($read);
        $todo = mysqli_fetch_all($result, MYSQLI_ASSOC);
        echo json_encode($todo);
    } else {
        $read = "SELECT * FROM `register`";
        $result = $conn->query($read);
        $todo = mysqli_fetch_all($result, MYSQLI_ASSOC);
        echo json_encode($todo);
    }
?>
