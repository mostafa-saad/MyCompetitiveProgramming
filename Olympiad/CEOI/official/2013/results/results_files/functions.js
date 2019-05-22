
window.defaultStatus = " ";
cookie_name = "layers";

function ch_m(obj,action) // change menu on mouseover/mouseout
{
  if (action == "over")
  {
    obj.style.cursor = "pointer";
    obj.className = "menu_over";
    window.status = "Expand or collapse this menu";
  }
  else
  {
    obj.style.cursor = "default";
    obj.className = "menu_out";
    window.status = " ";
  }
}

function sh_layer(id) // show/hide layer
{
  var submenu_id = "submenu" + id;
  var sign_id = "sign" + id;

  if (document.getElementById(submenu_id).style.display == "none")
  {
    document.getElementById(submenu_id).style.display = "";
    document.getElementById(sign_id).src = "images/minus.gif";
  }
  else
  {
    document.getElementById(submenu_id).style.display = "none";
    document.getElementById(sign_id).src = "images/plus.gif";
  }
  save_layers();
}

function ch_sm_over(obj,status) // change submenu on mouseover
{
  obj.style.cursor = "pointer";
  obj.className = "submenu_over";
  window.status = status;
}

function ch_sm_out(obj) // change submenu on mouseout
{
  obj.style.cursor = "default";
  obj.className = "submenu_out";
  window.status = " ";
}

function show_page(page)
{
  window.location = "index.php?page=" + page;
}

function load_layers()
{
  var start,end;
  var submenu_id,sign_id;
  var cookie_string,submenu_display;

  start = document.cookie.indexOf(cookie_name);
  if (start == -1)
    return null;

  start += 7;
  end = document.cookie.indexOf(";",start);
  if (end == -1)
    end = document.cookie.length;

  cookie_string = document.cookie.substring(start,end);

  for (i = 0; i < 3; i++)
  {
    submenu_display = cookie_string.substring(0,1);
    cookie_string = cookie_string.substring(2,cookie_string.length);
    submenu_id = "submenu" + i;
    sign_id = "sign" + i;

    if (submenu_display == "0")
    {
      document.getElementById(submenu_id).style.display = "none";
      document.getElementById(sign_id).src = "images/plus.gif";
    }
    else
    {
      document.getElementById(submenu_id).style.display = "";
      document.getElementById(sign_id).src = "images/minus.gif";
    }
  }
}

function save_layers()
{
  var cookie_string;

  cookie_string = cookie_name + "=";

  for (i = 0; i < 2; i++)
    if (document.getElementById("submenu" + i).style.display == "none")
      cookie_string += "0";
    else
      cookie_string += "1";

  cookie_string = cookie_string + ";";

  document.cookie = cookie_string;
}

function mouse_over(obj)
{
  obj.style.cursor = "pointer";
}

function mouse_out(obj)
{
  obj.style.cursor = "default";
}

function email(text)
{
  string = "ceoi2013";
  string += "@";
  string += "hsin";
  string += ".";
  string += "hr";

  document.write('<a href="mailto: ' + string + '">' + string + '</a>');
}
