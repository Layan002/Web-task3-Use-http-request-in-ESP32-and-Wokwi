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

$sql = "SELECT direction FROM movements ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    echo json_encode(["status" => "success", "direction" => $row["direction"]]);
} else {
    echo json_encode(["status" => "error", "message" => "No movements found"]);
}

$conn->close();
?>
