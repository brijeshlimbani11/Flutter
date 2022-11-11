<?php

    include("../Config/dbcon.php");

    if(isset($_POST["email"]) && isset($_POST["password"])) {
        $email = $_POST['email'];
        $password = $_POST['password'];

        $check = "SELECT * FROM `register` WHERE `email` = '$email' AND `password` = '$password' ";
        $result = mysqli_query($conn, $check);
        $count = mysqli_num_rows($result);

        if($count == 1) {
            echo json_encode("success");
        } else {
            echo json_encode("error");
        }
    }

?>

