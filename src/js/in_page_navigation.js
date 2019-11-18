/* eslint-disable */
(function ($) {
  'use strict';

  // Iterate each element, append an anchor id and append link to block list.
  $('#main-article h2').each(function(index) {
    $(this).attr('id', 'ipn-' + index);
    $('.toc ul').addClass('nav-menu').append(
      '<li class="nav-item"><a href="#ipn-' +
        index +
        '">' +
        $(this).text() +
        '</a></li>'
    );
  });
})(jQuery);
