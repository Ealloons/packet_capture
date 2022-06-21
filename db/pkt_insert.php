<?php 

    include('dbco.php');
    $pkt_name = $_POST["name"];
    $pkt_port = $_POST["port"];
   
    $stmt = $con->prepare("insert into danguerous_port(name,port) value('$pkt_name',$pkt_port);");
    
    $stmt->execute();
    echo "nothing";
    
    /*
    if ($stmt->rowCount() > 0)
    {
       $data = array(); 
       while($row=$stmt->fetch(PDO::FETCH_ASSOC))
       {
       	extract($row);    		
            	array_push($data,"['$src_ip'] =='$port'=> ['$dst_ip']");
            	
	}
	$string = implode("\n",$data);
	$json = json_encode($string, JSON_PRETTY_PRINT|JSON_UNESCAPED_UNICODE);
	echo $json;
		
    }
    */
    

?>
