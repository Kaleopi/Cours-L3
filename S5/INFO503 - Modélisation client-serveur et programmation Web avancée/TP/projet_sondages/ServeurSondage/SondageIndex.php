<?php
spl_autoload_register(function ($class) {
    include 'classes/' . $class . '.class.php';
});
// header("Content-type: application/json; charset=utf-8");

// Préparation de la requête
$options = [
  'http' =>
  [
    'method'  => 'POST',
    'header'  => 'Content-type: application/x-www-form-urlencoded',
    'content' => $_POST
    ]
  ];
  
  if($_POST['donnees']=="createSondage"){
    // var_dump($_POST);
     $_POST['questions'] = json_decode($_POST['questions']);
     $_POST['choix'] = json_decode($_POST['choix']);

    $sondage = new Sondage($_POST['responsable'],$_POST['titre'],$_POST['questions'],$_POST['choix']);
    // var_dump($sondage->getQuestions());
    // var_dump( $sondage);
    $sondage = json_encode($sondage);
    $monfichier = fopen('../src/sondage.json', 'w+');
    // 2 : on écrit
    fputs($monfichier, $sondage);
    // 3 : quand on a fini de l'utiliser, on ferme le fichier
    fclose($monfichier);
    
   }
?>
