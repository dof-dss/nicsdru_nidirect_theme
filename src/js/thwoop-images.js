/**
 * @file
 * Provides a script to thwoop (expand/contract) floated responsive images and display full content width
 * images in a modal.
 *
 */

/* eslint-disable */
(function ($, Drupal) {
  Drupal.behaviors.nicsdruOriginsThwoopImages = {
    attach: function attach (context) {
      // Make responsive image styles thwoopable.
      var thwoopImageSelector = '[data-picture-mapping*="_expandable"] > img, [data-picture-mapping*="_expandable"] > figure';
      var $thwoopImages = $(thwoopImageSelector, context);

      // Add a clickable/focusable wrapper and icon to indicate image is thwoopable.
      $thwoopImages.once('thwoop-toggle').each(function () {

        var $thwooper = $('<a class="thwooper" href="#"></a>');

        $thwooper.click(function (event) {
          event.preventDefault();

          var $thwoopimage = $(this).find('img, figure');
          var $thwoop_wrap = $(this).closest('.media-image');
          var thwoop_picture_mapping = $(this).parent().attr('data-picture-mapping');
          var modal = (thwoop_picture_mapping == 'inline_xl_expandable' || thwoop_picture_mapping == 'portrait_full_expandable');

          if ($(this).hasClass('thwooped')) {
            $(this).removeClass('thwooped');
            $(this).attr('aria-label', 'Enlarge');
            if (modal) {
              $thwoop_wrap.removeClass('thwooped-modal');
              // Just in case user scrolled page behind the modal, bring image back into view.
              $thwoop_wrap[0].scrollIntoView({
                block: 'center',
              });
            }
          } else {
            $(this).addClass('thwooped');
            if (modal) {
              $thwoop_wrap.addClass('thwooped-modal');
              $(this).attr('aria-label', 'Close');
            } else {
              $(this).attr('aria-label', 'Shrink');
            }
          }

          // Enable escape key if showing image in a modal.
          if (modal) {
            $(document).keydown(function(event) {
              if (event.keyCode == 27) {
                $thwoop_wrap.removeClass('thwooped-modal');
                $thwoopimage.removeClass('thwooped');
                // Just in case user scrolled page behind the modal, bring image back into view.
                $thwoop_wrap[0].scrollIntoView({
                  block: 'center',
                });
              }
            });
          }
        });

        $(this).wrap($thwooper);
      });
    }
  };
})(jQuery, Drupal);
