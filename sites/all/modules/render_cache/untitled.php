<?php
/**
 * {@inheritdoc}
 */
public function build() {
  $build = [];

  $build['#lazy_builder'] = ['icecream:lazyCallback', []]
  $build['#create_placeholder'] = TRUE;
  $build['#markup'] = 'This is being generated with a placeholder.
  It is time for ice cream. Hurray for ice cream!';

  return $build;
}