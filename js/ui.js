(function($,Drupal){Drupal.behaviors.nidirectui={attach:function attach(context){$(".card--multilink",context).once("nicsdruAccordions").each(function(index){$(this).on("click",function(){$(this).find(".card__links").toggle()})})}}})(jQuery,Drupal);