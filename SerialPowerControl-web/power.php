<?php
error_reporting(E_ALL);
$chan = dechex(bindec($_GET['c']));
$chan = '0x'.$chan;
$chan = chr($chan);
echo $chan;
  shell_exec('stty -F /dev/ttyUSB0 19200');
if(isset($_GET['p'])){
  shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
  shell_exec("echo -n ".$_GET['p']." > /dev/ttyUSB0");
}

?>
