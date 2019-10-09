<?php
  spl_autoload_register(function ($class) {
      include 'Classes/'.$class.'.php';
  });
  session_start();

  $user = new Utilisateur(1,"admin","admin");
  // var_dump($user);
  $resp = new Responsable($user);
  $resp->creerSondage(1,"Sondage n°1");
  var_dump($resp);
  // $q1 = new Question("Question 1", ["Oui","Non"]);
  // $q2 = new Question("Question 2", ["Kek","keK"]);
  // echo $q2->__toString();

  // echo $user->__toString();

?>
