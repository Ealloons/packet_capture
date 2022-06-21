<?php
if($_SERVER['REQUEST_METHOD']=='GET')
{
	$dv_id = $_GET["dv_id"];

	$result = new StdClass();

	$result->dv_id = "$dv_id";

	$result->dv_ip = "ewqeqw";

	$result->dv_mac = "eerr";

	echo json_encode($result, JSON_PRETTY_PRINT|JSON_UNESCAPED_UNICODE);	
}

?>
