<?php 

    error_reporting(E_ALL); 
    ini_set('display_errors',1); 
    include('dbco.php');
    if( ($_SERVER['REQUEST_METHOD'] == 'POST') && isset($_POST['submit']))
    {
        $id=$_POST['id'];
        $ip=$_POST['ip'];
        $mac=$_POST['mac'];
        if(empty($id)){
            $errMSG = "blink on id";
        }
        else if(empty($ip)){
            $errMSG = "blink on ip";
        }
        else if(empty($mac)){
            $errMSG = "blink on mac";
        }
        if(!isset($errMSG))
        {
            try{
                $stmt = $con->prepare('INSERT INTO t1(dv_id, dv_ip, dv_mac) VALUES(:id, :ip, :mac)');
                $stmt->bindParam(':id', $id);
                $stmt->bindParam(':ip', $ip);
                $stmt->bindParam(':mac',$mac);

                if($stmt->execute())
                {
                    $successMSG = "새로운 device를 추가했습니다.";
                }
                else
                {
                    $errMSG = "device 추가 에러";
                }

            } catch(PDOException $e) {
                die("Database error: " . $e->getMessage()); 
            }
        }

    }
?>

<html>
   <body>
        <?php 
        if (isset($errMSG)) echo $errMSG;
        if (isset($successMSG)) echo $successMSG;
        ?>
        
        <form action="<?php $_PHP_SELF ?>" method="POST">
            Id: <input type = "text" name = "id" />
            Ip: <input type = "text" name = "ip" />
            Mac: <input type = "text" name = "mac" />
            <input type = "submit" name = "submit" />
        </form>
   
   </body>
</html> 
