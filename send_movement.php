<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "robotmove";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $direction = $_POST['direction'];

    $sql = "INSERT INTO movements (direction) VALUES ('$direction')";

    if ($conn->query($sql) === TRUE) {
        echo json_encode(["status" => "success"]);
    } else {
        echo json_encode(["status" => "error", "message" => $conn->error]);
    }
}

$conn->close();
?>
