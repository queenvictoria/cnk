------
Status
------

1. Beagle method not tested, copied from Ubercart Beagle.

2. Code doesn't feel as clean as it could be.


--------------
Token billling
--------------

1. Use of recurring billing (ReBill) requires the NuSOAP library available at http://sourceforge.net/projects/nusoap/
   a. Install the Libraries API module (http://drupal.org/project/libraries)
   b.. Install the NuSOAP library to the module's directory so that the directory structure looks like this:
    sites/all/libraries/nusoap
    sites/all/libraries/nusoap/lib
    sites/all/libraries/nusoap/lib/nusoap.php

2. Select payment method "Token Payments"

3. Add the "Setup for eWAY token billing" action to the "Create a new
   account for an anonymous order" and "Assign an anonymous order
   rules. Logged in users will be set up automatically for token
   billing without needing any rules.
