<!doctype html>
<html>
    <head>
        <meta charset="UTF-8" />
        <title>Jakes Power Control &beta;</title>
        <link rel="stylesheet" href="themes/css/jqtouch.css" title="jQTouch">

        <!--<script src="src/lib/zepto.min.js" type="text/javascript" charset="utf-8"></script>  Uncomment the following two lines (and comment out the previous two) to use jQuery instead of Zepto. -->
        <script src="src/jqtouch.min.js" type="text/javascript" charset="utf-8"></script>  
      
        <script src="src/lib/jquery-1.7.min.js" type="application/x-javascript" charset="utf-8"></script> 
        <script src="src/jqtouch-jquery.js" type="application/x-javascript" charset="utf-8"></script> 
        <script type="text/javascript" charset="utf-8">
	function getChannel(){
		var chan = '00';
		$('#channel_select').children('input').each(function(){
			if($(this).attr('checked') == 'checked'){
				chan = chan+'1';
			}else{
				chan = chan+'0';	
			}
		});
		chan = chan+'0';
		return chan;
	}

            var jQT = new $.jQTouch({
                icon: 'jqtouch.png',
                icon4: 'jqtouch4.png',
                addGlossToIcon: false,
                startupScreen: 'jqt_startup.png',
                statusBar: 'black-translucent',
                themeSelectionSelector: '#jqt #themes ul',
                preloadImages: []
            });

            // Some sample Javascript functions:
            $(function(){
		$('#select_channel_toggle').click(function(){
			$('#channel_select').toggle();
		});
		
		$('.execute_event').click(function(){
			$id = $(this).attr('id');
			var c = getChannel();
			$.get("power.php", { e: $id, c:c }, function(data){console.log(data);});
			
		});
        $('.toggle_device').change(function(evt, data) {
 			//alert($(this).children('input').attr('checked'));
			$id = $(this).attr('id');
			var c = getChannel();
			if($(this).children('input').attr('checked') == 'checked'){
				$.get("power.php", { p: $id, c:c }, function(data){console.log(data);});
			}else{
				if($id == '1'){
					$id = 'A';
				}else if($id == '2'){
					$id = 'B';
				}else if($id == '3'){
					$id = 'C';
				}else if($id == '4'){
					$id = 'D';
				}
				$.get("power.php", { p: $id, c:c }, function(data){console.log(data);} );
			}
					
			
                });
                
            });
        </script>
        <style type="text/css" media="screen">
            #jqt.fullscreen #home .info {
                display: none;
            }
            div#jqt #about {
                padding: 100px 10px 40px;
                text-shadow: rgba(0, 0, 0, 0.3) 0px -1px 0;
                color: #999;
                font-size: 13px;
                text-align: center;
                background: #161618;
            }
            div#jqt #about p {
                margin-bottom: 8px;
            }
            div#jqt #about a {
                color: #fff;
                font-weight: bold;
                text-decoration: none;
            }
        </style>
    </head>
    <body>
            <div id="home" class="current">
                <div class="toolbar">
                    <h1>Jake's Room</h1>
                </div><br>
				<div class="toolbar">
					<h1>Devices:</h1>
                </div>
				
                <form class="scroll">
                    <ul class="edit rounded">
   
                        <li>Room<span class="toggle_device toggle" id="1"><input type="checkbox" checked="checked"/></span></li>  
                        <li>Electonics Desk<span class="toggle_device toggle"  id="2"><input type="checkbox" /></span></li> 
                        <li>Writing Desk<span class="toggle_device toggle"  id="3"><input type="checkbox" /></span></li> 
                        <li>Screens<span class="toggle_device toggle"  id="4"><input type="checkbox" /></span></li>
                      
                    </ul>
                </form>
				<div class="toolbar">
					<h1>Events:</h1>
                </div>
				<a href="#" class="execute_event grayButton" style="" id="home">Home</a>
				<a href="#" class="execute_event grayButton" style="" id="leave">Leave</a>
				<a href="#" class="execute_event grayButton" style="" id="leave">Sleep</a>
				
		<div style="text-align: center;">
			<span id="select_channel_toggle" class="button"> select channel</span>
			<div id="channel_select" style="display:none;">
<table border="0" bordercolor="transparent" style="margin:auto; background-color:transparent" width="85px" cellpadding="0" cellspacing="0">
	<tr>
		<td>1</td>
		<td>2</td>
		<td>3</td>
		<td>4</td>
		<td>5</td>
	</tr>

</table>
				<input id="channel_1" type="checkbox" checked="checked"/>
				<input id="channel_2" type="checkbox" checked="checked"/>		<input id="channel_3" type="checkbox" checked="checked"/>		<input id="channel_4" type="checkbox" />		<input id="channel_5" type="checkbox" checked="checked"/>	
			</div>
		</div>
            </div>

            
    </body>
</html>
