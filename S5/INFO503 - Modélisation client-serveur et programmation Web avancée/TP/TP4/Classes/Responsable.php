<?php
public class Responsable extends Utilisateur{
  protected $sondages;

  function __construct(){
    $sondages = array();
  }
}
