<?php
class Question{
  protected $intitule;
  protected $choix; //tableau de choix

  function __construct($intitule, $choix){
    $this->intitule = $intitule;
    $this->choix = $choix;
  }

  function __toString(){
    return "Intitulé : ".$this->intitule."</br>".implode(" - ",$this->choix);
  }
}
