<?php
public class Question{
  protected $intitule;
  protected $choix; //tableau de choix

  function __construct(string $intitule, array $choix){
    $this->intitule = $intitule;
    $this->choix = $choix;
  }

  function __toString(){
    return "Intitulé : ".$intitule."\n".implode(" - ",$choix);
  }
}
