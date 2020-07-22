/**
 * @file
 * Provides a script to collapse accordion sections and expand them when section headings are clicked.
 *
 */

/* eslint-disable */
(function ($, Drupal) {
  Drupal.behaviors.nicsdruAccordions = {
    attach: function attach (context) {

      $('.accordion', context).once('nicsdruAccordions').each(function(index) {

        // Need to know if this accordion has a visible title (H2)
        var acc_title_visible = ($(this).find('.accordion-heading').length)? true : false;

        // If the accordion has no title (H2), section headings should be H2s.
        if (!acc_title_visible) {
          $('.accordion-section-title').replaceWith(function(){
            return $('<h2 class="accordion-section-title" />').append($(this).contents());
          });
        }

        // Get the accordion section headings
        var $acc_headings = $(this).find('.accordion-section-title');

        // Need a unique prefix for heading buttons and section attributes.
        var prefix = 'accordion-' + index;

        $acc_headings.each(function(index) {

          // Turn section headings into buttons to toggle section collapse/expand.
          // Include appropriate aria attributes for accessibility.

          $(this)
            .wrapInner(function() {
              var $btn = $('<button></button>');
              $btn.attr('id', prefix + '-heading-' + index)
                .attr('aria-controls', prefix + '-section-' + index)
                .attr('aria-expanded', 'false')
                .click(function() {
                  var $target = $('#' + prefix + '-section-' + index);
                  var expanded = $(this).attr('aria-expanded') === 'true' || false;
                  $(this).attr('aria-expanded', !expanded);
                  $target.toggleClass('expanded', !$target.hasClass('expanded'));
                });
              return $btn;
            })
            .next('.accordion-section')
              .attr('id', prefix + '-section-' + index)
              .attr('aria-labelledby', prefix + '-heading-' + index);
        });
      });
    }
  };
})(jQuery, Drupal);
