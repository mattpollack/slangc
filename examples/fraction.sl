func Fraction (int int {int int}?)
| _ 0 = ?
| n d = { n d }

func fraction_add(Fraction Fraction Fraction?)
| a b = Fraction ((a.first * b.second) + (b.first * a.second)) (a.second * b.second)

func main([string] IO)
| _ =
  let f = match (Fraction 10 11) | ? = exit | f = f
  in 
  match (option_pipe f
    [
      (func (Fraction Fraction?) | a = fraction_add a (Fraction 1 1))
      (func (Fraction Fraction?) | a = fraction_add a (Fraction 1 1))
      (func (Fraction Fraction?) | a = fraction_add a (Fraction 1 1))
      (func (Fraction Fraction?) | a = fraction_add a (Fraction 1 1))
    ])
  | ? = print "derp"
  | f = print f.n "/" f.d