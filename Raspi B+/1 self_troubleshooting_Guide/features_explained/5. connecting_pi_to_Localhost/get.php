<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "guide_db";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
if (isset($_GET['person_id'],$_GET['problem_detected']))
	{
    	
		date_default_timezone_set("Asia/Kolkata");
		$date=	date("Y/m/d h:i:sa"); 
		$person_id = $_GET['person_id'];
                $problem_detected = $_GET['problem_detected'];
			
		
       $query = "INSERT INTO guide_tbl(Date,Person_Directed,Problem_Detected) VALUES ('$date','$person_id','$problem_detected')";
	
        $result = mysqli_query($conn, $query);
        
		if($result)
		{
           echo "Inserted Succesful";
		}
		else{echo "Error1";}
	}
	else
        {
		
		echo 'Enter All Data';
	}
     
	
?>