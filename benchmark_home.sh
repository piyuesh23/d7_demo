drush dis -y render_cache
ab -n 1 -c 1 http://dev.d7/content-listing > /dev/null
ab -n 30 -c 5 http://dev.d7/content-listing

drush en -y render_cache_views render_cache_comment
ab -n 1 -c 1 http://de.d7/content-listing > /dev/null
ab -n 30 -c 5 http://dev.d7/content-listing
