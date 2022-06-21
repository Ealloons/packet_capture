<?php 

    //error_reporting(E_ALL); 
    //ini_set('display_errors',1); 

    include('dbco.php');
        

    $stmt = $con->prepare('select * from dv_list;');
    $stmt->execute();

    if ($stmt->rowCount() > 0)
    {
    	
        $data = array(); 
	
	
        while($row=$stmt->fetch(PDO::FETCH_ASSOC))
        {
            extract($row);
	    /*
            array_push($data, 
                array('dv_id'=>$dv_id,
                'dv_ip'=>$dv_ip,
                'dv_mac'=>$dv_mac
            ));
            */
            $result = new StdClass();
	    $result->dv_id = "$dv_id";
            $result->dv_ip = "$dv_ip";
	    $result->dv_mac = "$dv_mac";
	    array_push($data,$result);
        }
	
	
        //header('Content-Type: application/json; charset=utf8');
        $json = json_encode($data, JSON_PRETTY_PRINT|JSON_UNESCAPED_UNICODE);
        echo $json;
    }

?>
