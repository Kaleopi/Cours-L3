<?php
class Responsable extends Utilisateur{
  protected $sondages;

  function __construct(Utilisateur $user){
    $this->id = $user->id;
    $this->login = $user->login;
    $this->mdp = $user->mdp;
    $sondages = array();
  }

  function creerSondage(int $id, string $titre){
    $sondage =  new Sondage($id, $titre);
    array_push($this->sondages,$sondage);
  }
}
