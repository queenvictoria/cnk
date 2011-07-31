; what is the difference between make and build ? in the cossey / buildkit example 
; `build` gets drupal core and patches it ( `distro` ) then retrieves the profile 
; and `make` gets contrib modules ( via buildkits drupal-org.make file ) and 
; additions from cossey

; so build would run first
; followed by make

; Build Kit taking over
; ---------------------
; Include Build Kit install profile makefile via URL
includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/drupal-org.make

; bring in other stuff from cossey's merch profile
; ------------------------------------------------
includes[] = https://raw.github.com/petercossey/merch/master/merch.make

; Contrib
; -------
; http://drupal.org/project/commerce

projects[addressfield][subdir] = "contrib"
projects[addressfield][version] = "1.x-dev"
projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.x-dev"
projects[entity][subdir] = "contrib"
projects[entity][version] = "1.x-dev"
projects[rules][subdir] = "contrib"
projects[rules][version] = "2.x-dev"
projects[libraries][subdir] = "contrib"

; http://drupal.org/node/1227018
; patch against rules short names
projects[rules][patch][1227018] = http://drupal.org/files/issues/schema-fix-1227018-p0.patch

projects[views][subdir] = "contrib"
projects[views][version] = "3.x-dev"
projects[commerce][subdir] = "contrib"
projects[commerce][version] = "1.x-dev"
projects[commerce_paypal][subdir] = "contrib"
projects[commerce_paypal][version] = "1.x-dev"
projects[commerce_product_display_manager][subdir] = "contrib"
projects[commerce_product_display_manager][version] = "1.x-dev"
projects[devel][subdir] = "developer"
projects[commerce_devel][subdir] = "developer"
projects[commerce_devel][version] = "1.x-dev"

; social bits for commerce
projects[votingapi][subdir] = "contrib"
projects[fivestar][subdir] = "contrib"
projects[fivestar][version] = "2.x-dev"
projects[addthis][subdir] = "contrib"
projects[addthis][version] = "2.1-beta1"
; fbconnect
; projects[fbconnect][subdir] = "contrib"
; projects[fbconnect][version] = "2.x-dev"
; http://drupal.org/node/795128
; current patches to fbconnect
; projects[fbconnect][patch][795128] = http://drupal.org/files/issues/795128-Port_fbconnect_to_d7-144.patch
; projects[fbconnect][patch][795128r] = http://drupal.org/files/issues/795128-README-update-145.patch

; or fb w/ fb_user
projects[fb][subdir] = "contrib"
projects[fb][version] = "3.x-dev"
; permissions fix which should allow fb_user to work without failing
projects[fb][patch][1173898] = http://drupal.org/files/issues/fb-permission-1173898-D7-no-prefix.patch

; libraries for either
; projects[] = fbconnect
; projects[] = fb
libraries[facebook-php-sdk][download][type] = "get"
libraries[facebook-php-sdk][download][url] = "http://github.com/facebook/php-sdk/tarball/v2.1.1"
libraries[facebook-php-sdk][download][tag] = v2.1.2
libraries[facebook-php-sdk][destination] = "libraries"   

