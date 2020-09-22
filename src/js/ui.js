/**
 * @file
 * Javascript for User Interface functions.
 *
 */

/* eslint-disable */
/*
  Toggle display of multiple links on card blocks.
 */
(function ($, Drupal) {
  Drupal.behaviors.nidirectui = {
    attach: function attach (context) {

      $('.card--multilink', context).once('nicsdruAccordions').each(function(index) {
        var links_wrapper = $(this).find('.card__links');

        $(this).on('click', function () {
          $(links_wrapper).toggle();
        })

        $(links_wrapper).find('a').click(function(e) {
          e.stopPropagation();
        });
      });
    }
  };
})(jQuery, Drupal);
