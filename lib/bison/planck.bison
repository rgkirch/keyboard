expr :
  space_pressed space_released { KEY_SPACE }
| space_pressed expr space_released { KEY_ALT }
