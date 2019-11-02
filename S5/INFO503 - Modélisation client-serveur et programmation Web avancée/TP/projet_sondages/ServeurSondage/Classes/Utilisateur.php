<?php
class Utilisateur{
  protected $login;
  protected $mdp;


  function __construct(string $login, string $mdp){
    $this->login = $login;
    $this->mdp = $mdp;

  }

  function __toString():string{
    return "Login : ".$this->getLogin()."\nMot de passe : ".$this->getMdp();
  }

  function getLogin():string{
    return $this->login;
  }

  function getMdp():string{
    return $this->mdp;
  }
}
