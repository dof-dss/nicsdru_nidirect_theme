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
        $(this).on('click', function () {
          $(this).find('.card__links').toggle();
        })
      });
    }
  };
})(jQuery, Drupal);
