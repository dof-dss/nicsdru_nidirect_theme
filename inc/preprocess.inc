<?php

/**
 * @file
 * Theme hook_preprocess functions.
 */

namespace Drupal\nicsdru_nidirect_theme;

use Drupal\Core\Template\Attribute;
use Drupal\Core\Render\Markup;
use Drupal\Component\Utility\Html;

/**
 * Implements hook_preprocess_html().
 */
function nicsdru_nidirect_theme_preprocess_html(array &$variables) {

  $route = \Drupal::routeMatch()->getRouteName();

  switch ($route) {
    case "nidirect_gp.gp_search":
      // Set a body class on the GP practice search page.
      $variables['attributes']['class'][] = 'page-search';
      break;
  }
}

/**
 * Implements hook_preprocess_page().
 */
function nicsdru_nidirect_theme_preprocess_page(array &$variables) {
  // Process node pages.
  if (!empty($variables['node'])) {
    $node = $variables['node'];
    if (isset($node) && method_exists($node, 'bundle')) {
      switch ($node->bundle()) {
        // Specific node types have a main and aside.
        case "article":
        case "application":
        case "health_condition":
        case "news":
        case "page":
          $variables['main_content_attr']->addClass(LayoutClasses::MAIN_SIDE);
          $variables['sidebar_second_attr']->addClass('ga-aside');
          break;

        // Specific node types have a main only.
        case "publication":
        case "embargoed_publication":
        case "landing_page":
          $variables['main_content_attr']->addClass(LayoutClasses::MAIN);
          break;

        // All the rest have a main with a limited width (includes
        // contact and gp_practice).
        default:
          $variables['main_content_attr']->addClass(LayoutClasses::MAIN_LIMITED);
          break;
      }
    }
  }

  // Process search view pages.
  $viewpage = \Drupal::routeMatch()->getParameter('view_id');
  if (isset($viewpage)) {
    switch ($viewpage) {
      case "health_conditions":
        $variables['main_content_attr']->addClass(LayoutClasses::SIDE_MAIN);
        if ($variables['content_wrapper_attr'] instanceof Attribute) {
          $variables['content_wrapper_attr']
            ->addClass('ga-main')
            ->setAttribute('role', 'presentation');
        }
        $variables['sidebar_first_attr']
          ->addClass('ga-aside')
          ->setAttribute('role', 'search')
          ->setAttribute('aria-label', t('filter search results'));
        break;

      case "publications":
        $variables['main_content_attr']->addClass(LayoutClasses::SIDE_MAIN);
        $variables['sidebar_first_attr']
          ->addClass('ga-aside')
          ->setAttribute('role', 'search')
          ->setAttribute('aria-label', t('filter search results'));
        break;

      case "search":
        $variables['main_content_attr']->addClass(LayoutClasses::MAIN_LIMITED);
        if ($variables['content_wrapper_attr'] instanceof Attribute) {
          $variables['content_wrapper_attr']
            ->addClass(['ga-main', 'search-content'])
            ->setAttribute('role', 'presentation');
        }
        break;
    }
  }

  // Process pages based on routes.
  $route = \Drupal::routeMatch()->getRouteName();

  switch ($route) {
    // Contacts page uses multiple routes defined in nidirect_contacts module.
    case 'nidirect_contacts.default':
    case 'nidirect_contacts.letter':
      $variables['main_content_attr']->addClass(LayoutClasses::MAIN_LIMITED);
      if ($variables['content_wrapper_attr'] instanceof Attribute) {
        $variables['content_wrapper_attr']
          ->addClass(['ga-main', 'list-content'])
          ->setAttribute('role', 'presentation');
      }
      break;

    // News landing page.
    case 'nidirect_news.news_listing':
      $variables['main_content_attr']->addClass(LayoutClasses::MAIN);
      if ($variables['content_wrapper_attr'] instanceof Attribute) {
        $variables['content_wrapper_attr']
          ->addClass(['ga-main', 'list-content'])
          ->setAttribute('role', 'presentation');
      }
      break;

    // Site theme term pages.
    case 'entity.taxonomy_term.canonical':
      // Set the section css classes for theme taxonomy terms.
      if ($variables['term']->bundle() == "site_themes") {
        $variables['main_content_attr']->addClass([
          'grid',
          'layout--theme-term',
        ]);
        if ($variables['content_wrapper_attr'] instanceof Attribute) {
          $variables['content_wrapper_attr']
            ->addClass(['ga-main', 'list-content'])
            ->setAttribute('role', 'presentation');
        }
        $variables['sidebar_second_attr']->addClass('section--popular');
      }
      break;

    // Webforms.
    case 'entity.webform.canonical':
      $variables['main_content_attr']->addClass(LayoutClasses::MAIN_LIMITED);
      if ($variables['content_wrapper_attr'] instanceof Attribute) {
        $variables['content_wrapper_attr']
          ->addClass(['ga-main', 'form-content'])
          ->setAttribute('role', 'presentation');
      }
      break;

    // Node preview pages.
    // Ensure the side-bar in the node preview is visible to accurately
    // reflect how the published node will look.
    case 'entity.node.preview':
      $node_preview = \Drupal::routeMatch()->getParameter('node_preview');
      $node_type = $node_preview->getType();

      switch ($node_type) {
        case 'article':
        case 'news':
        case 'application':
        case 'landing_page':
        case 'page':
          // Render Related Content block.
          $variables['page']['sidebar_second'][] = Helpers::blockContent('views_block__related_content_content_by_theme');
          break;

        case 'news':
          // Render Latest news block.
          $variables['page']['sidebar_second'][] = Helpers::blockContent('views_block__news_latest_news_block');
          break;

        case 'health_condition':
          // Render Health Conditions search block.
          $variables['page']['sidebar_second'][] = Helpers::blockContent('exposedformhealth_conditionssearch_sidebar_2');

          // Render Health Conditions AtoZ block.
          $variables['page']['sidebar_second'][] = Helpers::blockContent('healthconditionsatoz_sidebar_2');

          // Render Health Conditions Related block.
          $variables['page']['sidebar_second'][] = Helpers::blockContent('healthconditionsrelatedconditions');
          break;

        default:
          break;
      }

      // Display Social links block on the listed entity types.
      if (in_array($node_type, [
        'application',
        'article',
        'contact',
        'embargoed_publication',
        'health_condition',
        'news',
        'application',
        'landing_page',
        'page',
        'publication',
        'gp_practice',
      ])) {
        // Render Social Links block.
        $variables['page']['bottom_banner'][] = Helpers::blockContent('originssocialsharing');
      }

      // Add classes to main and sidebar regions to listed node types.
      switch ($node_type) {
        case "article":
        case "application":
        case "health_condition":
        case "news":
        case "page":
          $variables['main_content_attr']->addClass(LayoutClasses::MAIN_SIDE);
          $variables['sidebar_second_attr']->addClass('ga-aside');
          break;

        // Specific node types have a main only.
        case "publication":
        case "embargoed_publication":
        case "landing_page":
          $variables['main_content_attr']->addClass(LayoutClasses::MAIN);
          break;

        // All the rest have a main with a limited width (includes
        // contact and gp_practice).
        default:
          $variables['main_content_attr']->addClass(LayoutClasses::MAIN_LIMITED);
          break;
      }

      break;

    // Health conditions A to Z letter page
    // (see nidirect_health_conditions module).
    case 'nidirect_health_conditions.letter':
      $variables['main_content_attr']->addClass(LayoutClasses::SIDE_MAIN);
      if ($variables['content_wrapper_attr'] instanceof Attribute) {
        $variables['content_wrapper_attr']
          ->addClass(['ga-main', 'search-content'])
          ->setAttribute('role', 'presentation');
      }
      $variables['sidebar_first_attr']
        ->addClass('ga-aside')
        ->setAttribute('role', 'search')
        ->setAttribute('aria-label', t('filter search results'));
      break;

    default:
      break;
  }

  if (isset($variables['is_front']) && $variables['is_front'] == TRUE) {
    $front_classes = ['grid', 'layout--front'];
    $variables['main_content_attr']->addClass($front_classes);
    $variables['sidebar_second_attr']->addClass('section--popular');
  }
}

/**
 * Implements hook_preprocess_node().
 */
function nicsdru_nidirect_theme_preprocess_node(array &$variables) {
  $variables['show_title'] = TRUE;

  switch ($variables['node']->getType()) {
    case "article":
    case "application":
    case "contact":
    case "gp_practice":
    case "health_condition":
    case "news":
    case "page":
    case "publication":
    case "embargoed_publication":
      $variables['attributes']['class'][] = Html::cleanCssIdentifier('ga-main');
      $variables['attributes']['class'][] = Html::cleanCssIdentifier('article-content');
      break;

    case "featured_content_list":
      // Only show the title on the canonical node route.
      if (\Drupal::routeMatch()->getRouteName() != 'entity.node.canonical') {
        $variables['show_title'] = FALSE;
      }
      break;

    case "publication":
      // Change field label to 'Documents'.
      $variables['content']['field_attachment']['#title'] = t('Documents');
      break;

    case "landing_page":
    case "page":
      // Omit the title on these content types; causes trouble with search
      // indexing. Resolvable with either suitable block config or specific
      // node templates for these types.
      $variables['show_title'] = FALSE;
      break;
  }
}

/**
 * Implements hook_preprocess_block().
 */
function nicsdru_nidirect_theme_preprocess_block(array &$variables) {

  // If a card has multiple links, toggle the display of those
  // links when the card is clicked.
  if (in_array($variables['plugin_id'], [
    'inline_block:card_standard',
    'inline_block:card_wide',
  ])) {
    if ($variables['content']['field_link']['#items']->count() > 1) {
      $variables['content']['is_multilink'] = TRUE;
      $variables['#attached']['library'][] = 'nicsdru_nidirect_theme/nidirect-ui';
    }
    else {
      $variables['content']['is_multilink'] = FALSE;
    }
  }

  // Set the title for 'Most popular by term' block.
  $route = \Drupal::routeMatch();
  if ($variables['plugin_id'] === 'views_block:popular_content-pop_by_term' && $route->getRouteName() === 'entity.taxonomy_term.canonical') {
    $variables['label'] = t('Popular in @term', ['@term' => strtolower($route->getParameter('taxonomy_term')->label())]);
  }

}

/**
 * Implements hook_preprocess_page_title().
 */
function nicsdru_nidirect_theme_preprocess_page_title(&$variables) {

  // By default page titles are visible.
  $variables['title_visible'] = TRUE;

  // Preprocess titles on certain routes.
  $route = \Drupal::routeMatch();

  // Will need bits and pieces from the request for titles.
  $request = \Drupal::request();

  switch ($route->getRouteName()) {

    // Preprocess search page title.
    case "view.search.search_page":
      // Modify title if a search query is present.
      $query = $request->get('query');
      if (!empty($query)) {
        $variables['title'] = t('Search results');
      }
      // Add a subtitle to indicate the current page selected from the pager.
      $page = $request->get('page');
      if (!empty($page) && $page > 0) {
        $page = ++$page;
        $variables['title_subtitle'] = t('page :page', [':page' => $page]);
      }
      break;

    // Preprocess news listing page title.
    case "nidirect_news.news_listing":
      // Add a subtitle to indicate the current page selected from the pager.
      $page = $request->get('page');
      if (!empty($page) && $page > 0) {
        $page = ++$page;
        $variables['title_subtitle'] = t('page :page', [':page' => $page]);
      }
      break;

    // Preprocess contacts search page title.
    case "nidirect_contacts.default":
      // Add a subtitle to indicate the current page selected from the pager.
      $page = $request->get('page');
      if (!empty($page)) {
        $page = ++$page;
        $variables['title_subtitle'] = t('page :page', [':page' => $page]);
      }
      break;

    // Preprocess contacts A to Z page title.
    case "nidirect_contacts.letter":
      // Add a subtitle to indicate letter chosen from the A to Z.
      $letter = $route->getParameter('letter');
      if (!empty($letter)) {
        $variables['title'] = 'Contacts';
        $variables['title_subtitle'] = t('under :letter', [':letter' => strtoupper($letter)]);
      }
      break;

    // Preprocess health conditions search page title.
    case "view.health_conditions.search_page":
      // Add a subtitle to indicate showing results and the current page
      // selected from the pager.
      $page = $request->get('page');
      $search_query = $request->get('query_health_az');
      if (!empty($search_query) && empty($page)) {
        $variables['title_subtitle'] = t('search results');
      }
      if (!empty($search_query) && !empty($page)) {
        $page = ++$page;
        $variables['title_subtitle'] = t('search results page :page', [':page' => $page]);
      }
      break;

    // Preprocess health conditions A to Z listing title.
    case "nidirect_health_conditions.letter":
      // Add a subtitle to indicate letter chosen from the A to Z.
      $letter = $route->getParameter('letter');
      if (!empty($letter)) {
        $variables['title_subtitle'] = t('conditions under :letter', [':letter' => strtoupper($letter)]);
      }
      break;

    // Preprocess GP practice search page title.
    case "nidirect_gp.gp_search":
      // Add a subtitle to indicate the current page selected from the pager.
      $page = $request->get('page');
      if (!empty($page)) {
        $page = ++$page;
        $variables['title_subtitle'] = t('page :page', [':page' => $page]);
      }
      break;

    // Preprocess driving instructor search page title.
    case "view.driving_instructors.driving_instructor_results":
      // Add a subtitle to indicate showing results and the current page
      // selected from the pager.
      $page = $request->get('page');
      $search_query = $request->get('search_api_fulltext');
      if (!empty($search_query) && empty($page)) {
        $variables['title'] = t('Approved driving or motorcycle instructors');
        $variables['title_subtitle'] = t('search results');
      }
      elseif (!empty($search_query) && !empty($page)) {
        $page = ++$page;
        $variables['title'] = t('Approved driving or motorcycle instructors');
        $variables['title_subtitle'] = t('search results page :page', [':page' => $page]);
      }
      break;
  }
}

/**
 * Implements hook_preprocess_field().
 */
function nicsdru_nidirect_theme_preprocess_field(&$variables) {
  if ($variables['element']['#field_name'] == 'field_featured_content' && \Drupal::service('path.matcher')->isFrontPage()) {
    // Only show 3 items on the homepage.
    if (count($variables['items']) > 3) {
      $variables['items'] = array_slice($variables['items'], 0, 3);
    }
  }

  // Add a class to the anchor tag on application link fields & append the icon.
  if (isset($variables['element'])
    && $variables['element']['#field_name'] == 'field_link'
    && $variables['element']['#bundle'] == 'application'
  ) {
    foreach ($variables['items'] as $key => $item) {
      $icon = '<svg aria-hidden="true" class="ico ico-arrow-right"><use xlink:href="#arrow"></use></svg>';
      $title = $item['content']['#title'];
      $classes = ['call-to-action'];

      $formattedTitle = Markup::create($title . $icon);

      $variables['items'][0]['content']['#title'] = $formattedTitle;
      $variables['items'][0]['content']['#url']->setOption('attributes', ['class' => $classes]);
    }
  }
  // Amend classes on the standard address field output.
  if (isset($variables['element'])
    && $variables['element']['#field_type'] == 'address'
  ) {
    for ($i = 0; $i < count($variables['items']); $i++) {
      $variables['items'][$i]["content"]["#prefix"] = '<p class="adr" translate="no">';
      if (($key = array_search('address-line1', $variables['items'][$i]['content']['address_line1']['#attributes']['class'])) !== FALSE) {
        unset($variables['items'][$i]['content']['address_line1']['#attributes']['class'][$key]);
      }
      $variables['items'][$i]['content']['address_line1']['#attributes']['class'][] = 'street-address';
      if (($key = array_search('address-line2', $variables['items'][$i]['content']['address_line2']['#attributes']['class'])) !== FALSE) {
        unset($variables['items'][$i]['content']['address_line2']['#attributes']['class'][$key]);
      }
      $variables['items'][$i]['content']['address_line2']['#attributes']['class'][] = 'street-address';
      $i++;
    }
  }

  if (isset($variables['element'])
    && $variables['element']['#field_name'] == 'body'
    && $variables['element']['#bundle'] == 'webform'
  ) {
    $variables['body_summary'] = $variables['element']['#object']->body->summary;
  }
}

/**
 * Implements hook_preprocess_views_view().
 */
function nicsdru_nidirect_theme_preprocess_views_view(&$variables) {
  // Amend the role / labelling for search results pages.
  if ($variables['id'] === 'publications' && $variables['display_id'] === 'search_page') {
    $search_classes = [
      'card-deck',
      'border-bottom',
      'search-results',
    ];
    if (!isset($variables['attributes']['class'])) {
      $variables['attributes']['class'] = [];
    }
    $variables['attributes']['class'] = array_merge($variables['attributes']['class'], $search_classes);
    $variables['attributes']['role'] = 'region';
    $variables['attributes']['aria-label'] = t('search results');
  }
  if ($variables['view']->current_display == 'contacts_by_letter') {
    // Do not show search box if we are in a letter search.
    $route = \Drupal::routeMatch()->getRouteName();
    if ($route == "nidirect_contacts.letter") {
      $variables['exposed'] = NULL;
    }
  }
  if ($variables['id'] === 'popular_content' && $variables['display_id'] === 'pop_by_term') {
    $variables['attributes']['class'][] = 'sub-menu';
    $variables['attributes']['class'][] = 'sub-menu--popular';
  }
}

/**
 * Implements hook_preprocess_form().
 */
function nicsdru_nidirect_theme_preprocess_form(array &$variables) {
  switch ($variables['element']['#id']) {
    case "views-exposed-form-contacts-a-z-contacts-by-letter":
    case "views-exposed-form-contacts-contact-search":
    case "views-exposed-form-driving-instructors-driving-instructor-results":
    case "views-exposed-form-gp-practices-find-a-gp":
    case "views-exposed-form-health-conditions-search-page":
    case "views-exposed-form-publications-search-page":
      $variables['attributes']['class'][] = Html::cleanCssIdentifier('search-form');
      $variables['attributes']['class'][] = Html::cleanCssIdentifier('search-form--page');
      break;
  }
}

/**
 * Implements hook_preprocess_taxonomy_term().
 */
function nicsdru_nidirect_theme_preprocess_taxonomy_term(array &$variables) {
  if ($variables['term']->getVocabularyId() != 'site_themes') {
    // We are only interested in the 'site themes' vocab.
    return;
  }
  $cache_tags = [];
  // Add a custom cache tag for this taxonomy term 'listing' page.
  $cache_tags[] = 'taxonomy_term_list:' . $variables['term']->id();
  // Add the standard taxonomy term cache tag as well.
  $cache_tags[] = 'taxonomy_term:' . $variables['term']->id();
  // Render the 'articles by term' view and process the results.
  $results = _render_articles_by_term($cache_tags);
  // Render the 'site subtopics' view and process the results.
  $results += _render_site_subtopics($cache_tags);

  // Sort entries alphabetically (regardless of type).
  ksort($results);

  // Return as an 'item_list' themed render array, with
  // cache tags set appropriately.
  $variables['information_services_output'] = [
    '#theme' => 'item_list',
    '#items' => $results,
    '#cache' => [
      'tags' => $cache_tags,
    ],
  ];
}
