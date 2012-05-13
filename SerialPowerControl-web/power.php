
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"> 
<html lang="en"> 
<head> 
<meta http-equiv="X-UA-Compatible" content="IE=8"> 

<title>Power controller</title> 

</head> 
<body> 
<?php
error_reporting(E_ALL);


  exec('stty -F /dev/ttyUSB0 19200');
if(isset($_GET['p'])){
  shell_exec("echo '".$_GET['p']."' > /dev/ttyUSB0");
}

?>
</body>
</html>
