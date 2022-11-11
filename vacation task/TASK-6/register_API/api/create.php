<?php

    include("../config/dbcon.php");

    if(isset($_POST["username"]) && isset($_POST["email"]) && isset($_POST["password"]) && isset($_POST["number"])) {
        $name = $_POST["username"];
        $email = $_POST["email"];
        $password = $_POST["password"];
        $number = $_POST["number"];

        $insert = "INSERT INTO `register` (`username`, `email`, `password`, `number`) VALUES ('$name', '$email', '$password', '$number')";
        
        if ($conn->query($insert) === TRUE) {
            echo json_encode("success");
        } else {
            echo json_decode("error");
        }
    }
?>
