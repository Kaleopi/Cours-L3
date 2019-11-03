<?php 
class Question{
    private $intitule;
    private $choix = array();

  public function __construct(string $intitule, array $choix) {
    $this->intitule = $intitule;
    $this->choix = $choix;
  }

  public function getIntitule(){
    return $this->intitule;
  }

  public function getChoix(){
    return $this->choix;
  }

}