<?php
class Utilisateur{
  protected $id;
  protected $login;
  protected $mdp;

  function __construct(int $id, string $login, string $mdp){
    $this->id = $id;
    $this->login = $login;
    $this->mdp = $mdp;

  }

  function __toString():string{
    return "ID : ".$this->getId()."\nLogin : ".$this->getLogin()."\nMot de passe : ".$this->getMdp();
  }

  function getId():int{
      return $this->id;
  }

  function getLogin():string{
    return $this->login;
  }

  function getMdp():string{
    return $this->mdp;
  }
}
