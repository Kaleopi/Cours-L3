<?php
class Sondage{
  protected $id;
  protected $titre;
  protected $questions;

  function __construct(int $id, string $titre){
    $this->id = $id;
    $this->titre = $titre;
    $this->questions = array();
  }

  function getQuestions(){
    return $this->questions;
  }

  function addQuestion(Question $question){
    array_push($questions,$question);
  }
}
