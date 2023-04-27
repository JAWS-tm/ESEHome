$(".filter-select").each(function() {
    var classes = $(this).attr("class"),
        id      = $(this).attr("id"),
        name    = $(this).attr("name");
    var template =  '<div class="' + classes + '">';
        template += '<span class="filter-select-trigger">' + $(this).attr("placeholder") + '</span>';
        template += '<div class="filter-options">';
        $(this).find("option").each(function() {
          template += '<span class="filter-option ' + $(this).attr("class") + '" data-value="' + $(this).attr("value") + '">' + $(this).html() + '</span>';
        });
    template += '</div></div>';
    
    $(this).wrap('<div class="filter-select-wrapper"></div>');
    $(this).hide();
    $(this).after(template);
  });
  $(".filter-option:first-of-type").hover(function() {
    $(this).parents(".filter-options").addClass("option-hover");
  }, function() {
    $(this).parents(".filter-options").removeClass("option-hover");
  });
  $(".filter-select-trigger").on("click", function() {
    $('html').one('click',function() {
      $(".filter-select").removeClass("opened");
    });
    $(this).parents(".filter-select").toggleClass("opened");
    event.stopPropagation();
  });
  $(".filter-option").on("click", function() {
    $(this).parents(".filter-select-wrapper").find("select").val($(this).data("value"));
    $(this).parents(".filter-options").find(".filter-option").removeClass("selection");
    $(this).addClass("selection");
    $(this).parents(".filter-select").removeClass("opened");
    $(this).parents(".filter-select").find(".filter-select-trigger").text($(this).text());
  });