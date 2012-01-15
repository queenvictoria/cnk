; what is the difference between make and build ? in the cossey / buildkit example 
; `build` gets drupal core and patches it ( `distro` ) then retrieves the profile 
; and `make` gets contrib modules ( via buildkits drupal-org.make file ) and 
; additions from cossey

; so build would run first
; followed by make

; Build Kit taking over
; ---------------------
; Include Build Kit install profile makefile via URL
; includes[] = http://drupalcode.org/project/buildkit.git/blob_plain/refs/heads/7.x-2.x:/drupal-org.make

api = 2
core = 7.x

; bring in other stuff from cossey's merch profile
; ------------------------------------------------
; includes[] = https://raw.github.com/petercossey/merch/master/merch.make

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

; laudanum stock
projects[admin][subdir] = "contrib"
projects[transliteration][subdir] = "contrib"
projects[token][subdir] = "contrib"
projects[pathauto][subdir] = "contrib"
projects[globalredirect][subdir] = "contrib"
projects[xmlsitemap][subdir] = "contrib"
projects[google_analytics][subdir] = "contrib"
projects[wysiwyg][subdir] = "contrib"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.4.2/ckeditor_3.4.2.tar.gz"
projects[features][subdir] = "contrib"
; patch features to handle shortcut sets http://drupal.org/node/986968
projects[features][patch][986968] = http://drupal.org/files/issues/features.shortcut_sets_0.patch

; dependencies for cnk features
projects[link][subdir] = "contrib"

; http://drupal.org/node/1227018
; patch against rules short names - committed  August 1, 2011 
; projects[rules][patch][1227018] = http://drupal.org/files/issues/schema-fix-1227018-p0.patch

projects[views][subdir] = "contrib"
projects[views][version] = "3.x-dev"
projects[commerce][subdir] = "contrib"
projects[commerce][version] = "1.x-dev"
projects[commerce_eway][subdir] = "contrib"
projects[commerce_eway][version] = "1.x-dev"
; library to support commerce_eway
libraries[nusoap][download][type] = "get"
libraries[nusoap][download][url] = "http://downloads.sourceforge.net/project/nusoap/nusoap/0.9.5/nusoap-0.9.5.zip"
libraries[nusoap][destination] = "libraries"   

projects[commerce_australia][subdir] = "contrib"
projects[commerce_australia][version] = "1.x-dev"
projects[commerce_paypal][subdir] = "contrib"
projects[commerce_paypal][version] = "1.x-dev"
projects[commerce_stock][subdir] = "contrib"
projects[commerce_stock][version] = "1.x-dev"
projects[commerce_shipping][subdir] = "contrib"
projects[commerce_shipping][version] = "1.x-dev"
projects[commerce_addressbook][subdir] = "contrib"
projects[commerce_addressbook][version] = "1.x-dev"
projects[commerce_shipping_flat_rate][subdir] = "contrib"
projects[commerce_shipping_flat_rate][version] = "1.x-dev"
projects[commerce_delivery][subdir] = "contrib"
projects[commerce_delivery][version] = "1.x-dev"
projects[commerce_product_display_manager][subdir] = "contrib"
projects[commerce_product_display_manager][version] = "1.x-dev"
projects[commerce_coupon][subdir] = "contrib"
projects[commerce_coupon][version] = "1.x-dev"
projects[commerce_features][subdir] = "contrib"
projects[commerce_features][version] = "1.x-dev"
projects[commerce_google_analytics][subdir] = "contrib"
projects[commerce_google_analytics][version] = "1.x-dev"
projects[commerce_product_bundle][subdir] = "contrib"
projects[commerce_product_bundle][version] = "1.x-dev"

; sandbox projects
; checkout progress
; http://git.drupal.org/sandbox/webmasterkai/1291268.git commerce_checkout_progress
; ajax cart
; git clone http://git.drupal.org/sandbox/webmasterkai/1299260.git dc_cart_ajax

projects[devel][subdir] = "developer"
projects[devel][subdir] = "devel_themer"
projects[commerce_devel][subdir] = "developer"
projects[commerce_devel][version] = "1.x-dev"
projects[module_filter][subdir] = "developer"

; social bits for commerce
projects[votingapi][subdir] = "contrib"
projects[fivestar][subdir] = "contrib"
projects[fivestar][version] = "2.x-dev"
; permission for anon users to view rating http://drupal.org/node/1247368
; projects[fivestar][patch][1247368] = http://drupal.org/files/issues/fivestar-see-avarage-1247368-5.diff
; updated 
projects[fivestar][patch][1247368-8] = https://raw.github.com/queenvictoria/cnk/master/patches/fivestar-see-average-1247368-8.patch

; projects[addthis][subdir] = "contrib"
; projects[addthis][version] = "2.1-beta1"
projects[sharethis][subdir] = "contrib"
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
; permissions fix which should allow fb_user to work without failing - rolled into dev by 19/8/2011
; projects[fb][patch][1173898] = http://drupal.org/files/issues/fb-permission-1173898-D7-no-prefix.patch
; user fix array_flip http://drupal.org/node/1064250
; no longer required
; projects[fb][patch][1064250] = http://drupal.org/files/issues/fb_user.module.patch

; libraries for either
; projects[] = fbconnect
; projects[] = fb
; neither supports api v3 yet so pin to latest v2
libraries[facebook-php-sdk][download][type] = "get"
; fb now supports 3
libraries[facebook-php-sdk][download][url] = "http://github.com/facebook/php-sdk/tarball/v3.1.1"
; libraries[facebook-php-sdk][download][tag] = v2.1.2
libraries[facebook-php-sdk][destination] = "libraries"   

; themes
projects[tao][subdir] = "contrib"
projects[tao][version] = 3.0-beta3
projects[rubik][subdir] = "contrib"
projects[rubik][version] = 4.0-beta6
projects[omega][subdir] = "contrib"