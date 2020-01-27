/* eslint-disable */
(function ($, Drupal) {
  Drupal.behaviors.nicsdruNidirectToc = {
    attach: function attach (context) {
      var tocHeadings = $('#main-article h2');
      var $tocList = $('<ul class="nav-menu" />');
      var $headingText = Drupal.t('On this page');
      var $skipTocText = Drupal.t('Skip table of contents');
      var $jumpTocText = Drupal.t('Jump to table of contents');

      if (tocHeadings.length > 2) {
        // Iterate each element, append an anchor id and append link to block list.
        $(tocHeadings, context).once('toc').each(function(index) {
          $(this).attr('id', 'toc-' + index);
          $tocList.append(
            '<li class="nav-item"><a href="#toc-' +
            index +
            '">' +
            $(this).text() +
            '</a></li>'
          );
        });

        // Create 2 TOC navs (only 1 will be visible, depending on screen size).
        // TOC for the main area, allow this to be read by screen readers etc.
        var $tocMain = $('<nav class="sub-menu toc toc-main" aria-labelledby="toc-main-heading" />');
        $tocMain.append('<h2 id="toc-main-heading" class="menu-title">' + $headingText + '</h2>',
                        '<a href="#toc-main-skip" class="skip-link visually-hidden focusable">' +
                          $skipTocText +
                        '</a>',
                        $tocList,
                        '<a id="toc-main-skip"></a>');
        $('.page-summary').after('<a href="#toc-aside" class="skip-link visually-hidden focusable skip-link__toc-aside">' + $jumpTocText + '</a>', $tocMain);

        // TOC for the main area, allow this to be read by screen readers etc.
        var $tocAside = $('<nav class="sub-menu rel-menu toc toc-aside" id="toc-aside" aria-hidden="true" />');
        $tocAside.append('<h2 id="toc-heading-aside" class="menu-title">' + $headingText + '</h2>',
          $tocList.clone());
        $('.layout-sidebar-second').prepend($tocAside);
      }
    }
  };
})(jQuery, Drupal);
