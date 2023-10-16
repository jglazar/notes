# Cryptocurrencies

## 3Blue1Brown Bitcoin

Imagine a group of friends that keep a common public ledger recording
transactions between members

Anybody can add a line! We need validation, and a simple signature won't do.
  * Digital signature encodes transaction message with your private key
  * People can validate your signature using the message and your public key
  * Each transaction message has a unique ID, to prevent copying lines

Prevent racking up charges by forcing everyone to put up "ledger bucks" at
beginning. Prevents people from charging more than their deposit

The ledger is decentralized. Each agent has own copy of ledger
  * Everyone broadcasts transactions. But who to trust?
  * Trust the person's ledger with the most "work" done
    * Proof of work: force ppl to find number that, when appended to transaction
      message, produces SHA256 hash with leading n zeros (expected 2^n work)
    * Integer n is selected to take ~10 min. Adjusted with more miners.
    * So, longer blockchains have more computational work done

A group (block) of transactions is added in a sequential chain. 
  * Each block has hash of previous block as a header. Prevents reordering
  * Miners collect transactions into blocks, then calculate magic number, then
    append to blockchain and broadcasts message
    * Miners earn small block reward for this work. Introduces new currency into
      economy
    * All new money is generated from block rewards. These halve periodically to
      cap out at 21M Bitcoin total.
    * Transaction fees paid by proposers incentivize miners to include
      their transaction in the blockchain
  * Each block is limited to 2400 transactions. Causes higher transaction fees

Fraud is hard to keep up. You'd need to append fraudulent block, then all next
blocks forever
  * Implies that you should wait for a few more blocks before trusting a block

## MIT MAS.62 -- Cryptocurrency engineering and design

### Motivation

Money evolved way to trade goods, or to simplify receipts (wool storage, e.g.)

US money has value bc gov't backs it up and we all agree upon it. Crypto has
value bc we think it does

Traditional banks have centralized ledgers. Transactions are validated with ID
and guaranteed by bank
  * Allows remote payment
  * Bank is central point of failure. Can have corrupt employees. Can be
    delayed or banned. Privacy concerns

Fundamental problem with e-cash is copying. Allows double-spend.
  * Digital signature validates bank giving coin to Alice, who can pay Bob 
  * Bob can validate coin with bank. Bank links coin's serial number to specific
    transactions b/t parties to prevent double-spend

Chaumian e-cash allows Alice to choose serial number s.t. bank doesn't know it
  * Bank can verify on "blinded" secret number
  * Alice gives Bob the coin. Bob cashes in with bank. Bank never sees number,
    so cannot link to transaction with Alice
  * Bank cannot link transactions unless Alice gives same coin to 2 people. Can 
    punish Alice
  * However, bank can still ban people

### Hashes

Desired properties
  * Take in any size, output same size
  * Should have half 0s and half 1s
  * Avalanche effect -- change 1 bit input --> half of output bits change
  * Preimage resistance -- cannot find input corresponding to output w/o brute
  * Collision resistance -- cannot find distinct x and z s.t. hashes are equal
    * Actually "only" takes sqrt(output space) due to Birthday Effect

Collision resistance is more difficult to obtain than preimage resistance
  * SHA-1 and MD5 have been broken

There's no proof that true hash functions exist
  * New hash functions are typically found via trial and error. Few proofs
  * Not based on cool number theory insights
  * Breaks require proofs/algorithms, not just counterexamples

Hashes are used for:
  * Names -- filename = hash(file)
  * References/pointers. But hashes disallow cycles, unlike pointers
  * Commitments -- show hash(x), then later reveal x. ppl can verify
    * Add random numbers at end of message to prevent brute force guessing

Signatures require 3 functions
  * GenerateKeys() -- return secret and public key pair
  * Sign(secretKey, message) -- signs message, returns signature
  * Verify(publicKey, message, signature) -- return T/F

Can construct signature system from hashes alone -- Lamport Signatures
  * Turns out Lamport Signatures are resistant to quantum computers
