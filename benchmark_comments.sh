drush dis -y render_cache
ab -n 1 -c 1 http://dev.d7/node/38 > /dev/null
ab -n 30 -c 5 http://dev.d7/node/38

drush en -y render_cache_views render_cache_comments
ab -n 1 -c 1 http://de.d7/node/38 > /dev/null
ab -n 30 -c 5 http://dev.d7/node/38
