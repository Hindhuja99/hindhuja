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
?>

<!DOCTYPE html>
<html>


<head>
<title>Troubleshooting Guide</title>
    <link rel="stylesheet" type="text/css" href="demo.css" media="all" />
    <link rel="stylesheet" type="text/css" href="style.css" media="all" />
    <style>
#customers {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
	margin:auto;
}

#customers td, #customers th {
    border: 1px solid #ddd;
    padding: 8px;
}

#customers tr:nth-child(even){background-color: #f2f2f2;}

#customers tr:hover {background-color: #ddd;}

#customers th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
}
</style>
    
</head>
<body>

<div align="center">
			<!-- freshdesignweb top bar -->
			<header>
				<h1>PROBLEMS DETECTED</h1>
            </header>       
            <?php  
 
 $query = "SELECT * FROM guide_tbl";  
 $result = mysqli_query($conn, $query);
 ?>
<table id="customers">
  <tr>
    <th>S.No</th>
    <th>Customer_ID</th>
    <th>Problem_Detected</th>
    <th>Date</th>
    <th>Person_Directed</th>
  </tr> 
  <tr>
                                                          <?php  
														  $i=0;
														  if (mysqli_num_rows($result) > 0) {
														  while($row = mysqli_fetch_assoc($result))  
														  {  
														  $i++;
														  ?>  
                                                        <td><?php echo $i; ?></td>
                                                        <td><?php echo "Model No. 5AB26726" ?></td>
                                                        <td><?php echo $row["Problem_Detected"]; ?></td>
							<td><?php echo $row["Date"]; ?></td>
                                                        <td><?php echo $row["Person_Directed"]; ?></td>
                                                        
                                                            
    
  </tr>
                                                        <?php  
														  }  
														  }
														  ?>

</table>

</div>      
</div>

</body>
</html>


