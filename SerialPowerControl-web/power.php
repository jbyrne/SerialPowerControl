<?php
	error_reporting(E_ALL); 
	$chan = dechex(bindec($_GET['c']));
	$chan = '0x'.$chan;
	$chan = chr($chan);
	shell_exec('stty -F /dev/ttyUSB0 19200');
?>
<html>
<head>

		<meta name="apple-mobile-web-app-capable" content="yes">
		<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
        <title>Jakes Power Control ß </title>
        <script type="text/javascript" charset="utf-8">
        </script>
</head>
 <body style="background-color: #555658; color:#D5D6D7">

	<div style="text-align: center;">
		<?php
			if(isset($_GET['p'])){
			  shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
			  shell_exec("echo -n ".$_GET['p']." > /dev/ttyUSB0");
			}else if(isset($_GET['e'])){
				if($_GET['e']== 'home'){
						shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
						shell_exec("echo -n 1 > /dev/ttyUSB0");
						shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
						shell_exec("echo -n 4 > /dev/ttyUSB0");
						
						echo 'Home Power Profile <br>';
					
				}else if($_GET['e']== 'leave'){
						shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
						shell_exec("echo -n A > /dev/ttyUSB0");
						shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
						shell_exec("echo -n B > /dev/ttyUSB0");
						shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
						shell_exec("echo -n C > /dev/ttyUSB0");
						shell_exec("echo -n ".$chan." > /dev/ttyUSB0");	
						shell_exec("echo -n D > /dev/ttyUSB0");
						
						echo 'Leaving Power Profile <br>';
				}
			}
		?>


		</div>
</body>
</html>