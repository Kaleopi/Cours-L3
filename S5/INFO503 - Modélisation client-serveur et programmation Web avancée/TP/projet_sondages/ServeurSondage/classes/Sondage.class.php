<?php 
require ('Question.class.php');
class Sondage{
  private $responsable;
  private $titre;
  private $questions = array();

  public function __construct(string $resp, string $tit, array $quest, array $ch) {
    $this->responsable = $resp;
    $this->titre = $tit;
    for($i=0 ; $i<sizeof($quest) ;$i++){
      $question = new Question($quest[$i], $ch[$i]);
      array_push($this->questions,$question);
    }

  }

  public function getResponsable(){
    return $this->responsable;
  }

  public function getTitre(){
    return $this->titre;
  }

  public function getQuestions(){
    return $this->questions;
  }
}