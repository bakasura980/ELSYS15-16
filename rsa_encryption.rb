require 'prime'

class KeyGenerator
  attr_accessor (:p, :q)

  def self.validate_primes
    return p.prime? && q.prime?
  end

  n = p * q
  fn =  n − p + q − 1

  def self.suggest_e
    for i in 2..fn
      if ! fn.gcd(i).nil?
        p e + " "
      end
    end
  end

  def self.generate_d
    for d in 0..fn
      if (d * e) % fn == 1
        return d
      end
    end
  end

  d = generate_d

  def self.encrypt m
    c = m.to_i ** e
    c = c % n
  end

  def self.decrypt c
    m = c ** d
    m = m % n
  end
end
