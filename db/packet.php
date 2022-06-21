<?php 

    include('dbco.php');
    $dv_ip = $_POST["dv_ip"];
    
    $stmt = $con->prepare("select * from pkt_log where src_ip like '$dv_ip' OR dst_ip like '$dv_ip';");
    
    $stmt->execute();
    if ($stmt->rowCount() > 0)
    {
       $data = array(); 
       while($row=$stmt->fetch(PDO::FETCH_ASSOC))
       {
       	extract($row);    		
            	array_push($data,"['$time']  :  ['$src_ip']  =='$port'=>  ['$dst_ip']");
            	
	}
	$string = implode("\n",$data);
	$json = json_encode($string, JSON_PRETTY_PRINT|JSON_UNESCAPED_UNICODE);
	echo $json;
		
    }
    

?>
