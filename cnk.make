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
projects[views][subdir] = "contrib"
projects[views][version] = "3.x-dev"
projects[commerce][subdir] = "contrib"
projects[commerce][version] = "1.x-dev"