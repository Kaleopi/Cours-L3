<?php
header("Content-type: application/json; charset=utf-8");
// var_dump($_POST);

// Préparation de la requête
$options = [
  'http' =>
  [
    'method'  => 'POST',
    'header'  => 'Content-type: application/x-www-form-urlencoded',
    'content' => $_POST['donnees']
    ]
  ];

  if($_POST['mode']=="connexion"){
    $URL = "http://localhost:8080/login.php";
  }
  else{
    if($_POST['mode']=="inscription"){
      $URL = "http://localhost:8080/create.php";
    }
  }
  // Envoi de la requête et lecture du JSON reçu
  // Remplacez l'URL par l'adresse locale vers generateur.php
    $contexte  = stream_context_create($options);
    

    //RECEPTION SERV AUTH
    if(($jsonTexte = @file_get_contents($URL, false, $contexte)) !== false) {
      // Analyse du JSON reçu
        $tableau = json_decode($jsonTexte, true);
        if($tableau['code'] == "OKconnexion"){echo "<p>Bravo !!! Vous êtes connecté !!!</p>";}
        elseif($tableau['code'] == "OKinscription"){echo "<p>Bravo, vous êtes inscrit et vous pouvez maintenant vous connecter.</p>";}
        else{echo "<p>Erreur de connexion ! L'erreur est <strong>".$tableau['message']."</strong></p>";}
    }
    else
        echo "<p>Une erreur est survenue lors de la récupération des données.</p>";
?>
