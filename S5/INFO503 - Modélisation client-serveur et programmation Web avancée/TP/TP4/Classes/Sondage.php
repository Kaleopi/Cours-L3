<?php
public class Sondage{
  protected $questions;

  function __construct(){
    $this->questions = array();
  }

  // function __toString(){
  //
  // }

  function getQuestions(){
    return $this->questions;
  }
}
