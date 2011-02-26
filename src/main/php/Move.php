<?php

class Move {

    private $from;
    private $jumped;
    private $to;
    
    /**
     * @param from
     * @param jumped
     * @param to
     */
    public function Move($from, $jumped, $to) {
        $this->from = $from;
        $this->jumped = $jumped;
        $this->to = $to;
    }

    public function getFrom() {
        return $this->from;
    }


    public function getJumped() {
        return $this->jumped;
    }


    public function getTo() {
        return $this->to;
    }


    public function toString() {
        return $this->from . " -> " . $this->jumped . " -> " . $this->to;
    }
}
?>