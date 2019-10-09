<?php
public class Utilisateur{
  protected $id;
  protected $login;
  protected $mdp;

  function __construct(int $id, string $login, string $mdp){
    $this->id = $id;
    $this->login=$login;
    $this->mdp=$mdp;
  }

  function __toString():string{
    return "ID : ".$id."\nLogin : ".$login."\nMot de passe : ".$mdp;
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
