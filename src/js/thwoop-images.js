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
        $(this).after('<a class="thwooper" href="#">Enlarge</a>');
      });

      // Click or keypress toggles thwoop.
      $('.thwooper').click(function (event) {
        event.preventDefault();
        var $thwoopimage = $(this).prev('img, figure');
        var $thwoop_wrap = $(this).closest('.media-image');
        var thwoop_picture_mapping = $thwoopimage.parent().attr('data-picture-mapping');
        var modal = false;

        if (thwoop_picture_mapping == 'inline_xl_expandable' || thwoop_picture_mapping == 'portrait_full_expandable') {
          modal = true;

          // Enable escape key to close modal.
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

        if ($thwoopimage.hasClass('thwooped')) {
          $thwoopimage.removeClass('thwooped');
          $(this).text('title', 'Enlarge');
          if (modal) {
            $thwoop_wrap.removeClass('thwooped-modal');
            // Just in case user scrolled page behind the modal, bring image back into view.
            $thwoop_wrap[0].scrollIntoView({
              block: 'center',
            });
          }
        } else {
          $thwoopimage.addClass('thwooped');
          if (modal) {
            $thwoop_wrap.addClass('thwooped-modal');
            $(this).text('Close');
          } else {
            $(this).text('Shrink');
          }
        }
      });
    }
  };
})(jQuery, Drupal);
