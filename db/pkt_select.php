<?php 

    include('dbco.php');
   
    $stmt = $con->prepare("select * from danguerous_port");
    
    $stmt->execute();
    if ($stmt->rowCount() > 0)
    {
       $data = array(); 
       while($row=$stmt->fetch(PDO::FETCH_ASSOC))
       {
       	extract($row);    		
            	array_push($data,"$name         :         $port");
            	
	}
	$string = implode("\n",$data);
	$json = json_encode($string, JSON_PRETTY_PRINT|JSON_UNESCAPED_UNICODE);
	echo $json;
		
    }
    
    

?>
