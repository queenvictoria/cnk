<?php

class eway_cvn_xml extends eway_xml_common {

   function __construct($settings) {
     parent::__construct($settings);
     $this->url = ($this->testing) ? 'https://www.eway.com.au/gateway_cvn/xmltest/testpage.asp' : 'https://www.eway.com.au/gateway_cvn/xmlpayment.asp';
   }

   function prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail) {
     parent::prepare_request ($settings, $description, $charge, $credit_card, $address, $order_id, $uid, $mail);
     $this->xml_data['ewayCVN'] = $credit_card['code'];
   }

}